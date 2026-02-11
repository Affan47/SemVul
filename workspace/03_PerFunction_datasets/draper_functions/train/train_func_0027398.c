yy_destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor){
  switch( yymajor ){


    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
#line 22 "./mod_ssi_exprparser.y"
{ buffer_free((yypminor->yy0)); }
#line 352 "mod_ssi_exprparser.c"
      break;
    default:  break;
  }
}
