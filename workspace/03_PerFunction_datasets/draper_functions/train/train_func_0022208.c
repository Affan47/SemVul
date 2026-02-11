read_transforms(count)
int count;
{
  int i,j,n;
  REAL value;
  MAT2D(temp_mat,MAXCOORD+1,MAXCOORD+1);

  lists_flag = 1;
  if ( count > 0 ) transform_count = count+1;
  else
  {

    if ( (tok = gettok(INTEGER_)) != INTEGER_ )
    { kb_error(1748,"Missing number of transforms.\n",DATAFILE_ERROR);
      transform_count = 1;
    }
    else transform_count = yylval.i+1;
  }

  if ( view_transforms )
  { free_matrix3(view_transforms); view_transforms = NULL;}

  if ( transform_count <= 0 ) return;
  view_transforms = dmatrix3(transform_count,SDIM+1,SDIM+1);
  set_view_transforms_global();
  allocate_transform_colors(transform_count);
  view_transform_det = (int*)mycalloc(transform_count,sizeof(int));
  matcopy(view_transforms[0],identmat,SDIM+1,SDIM+1);
  transform_colors[0] = SAME_COLOR;
  view_transform_det[0] = 1;


  for ( n = 1 ; n < transform_count ; n++ )
  { tok = yylex();
    if ( tok == COLOR_ )
    { if ( (tok = gettok(INTEGER_)) != INTEGER_ )
         kb_error(1749,"Missing transform color.\n",DATAFILE_ERROR);
      transform_colors[n] = yylval.i;
      transform_colors_flag = 1;
    }
    else if ( tok == SWAP_COLORS_ )
    { transform_colors[n] = SWAP_COLORS;
      transform_colors_flag = 1;
    }
    else
    { transform_colors[n] = SAME_COLOR;
      unput_tok();
    }
    for ( i = 0 ; i <= SDIM ; i++ )
    { for ( j = 0 ; j <= SDIM ; j++ )
      { if ( read_const(&value) <= 0 )
        { kb_error(1750,"Not enough values for transform matrix.\n",
             DATAFILE_ERROR);
          return;
        }
        view_transforms[n][i][j] = value;
      }
      matcopy(temp_mat,view_transforms[n],SDIM+1,SDIM+1);
      if ( determinant(temp_mat,SDIM+1) > 0.0 )
         view_transform_det[n] = 1;
      else  view_transform_det[n] = -1;
    }
  }
  transforms_flag = 1;
  lists_flag = 0;
  if ( n == transform_count ) tok = yylex();
}
