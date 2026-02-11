Insert_String(FORM *form, int row, FIELD_CELL *txt, int len)
{
  FIELD *field = form->current;
  FIELD_CELL *bp = Address_Of_Row_In_Buffer(field, row);
  int datalen = (int)(After_End_Of_Data(bp, field->dcols) - bp);
  int freelen = field->dcols - datalen;
  int requiredlen = len + 1;
  FIELD_CELL *split;
  int result = E_REQUEST_DENIED;

  if (freelen >= requiredlen)
    {
      wmove(form->w, row, 0);
      myINSNSTR(form->w, txt, len);
      wmove(form->w, row, len);
      myINSNSTR(form->w, &myBLANK, 1);
      return E_OK;
    }
  else
    {


      if ((row == (field->drows - 1)) && Growable(field))
	{
	  if (!Field_Grown(field, 1))
	    return (E_SYSTEM_ERROR);

	  bp = Address_Of_Row_In_Buffer(field, row);
	}

      if (row < (field->drows - 1))
	{
	  split =
	    After_Last_Whitespace_Character(bp,
					    (int)(Get_Start_Of_Data(bp
								    + field->dcols
								    - requiredlen,
								    requiredlen)
						  - bp));


	  datalen = (int)(split - bp);
	  freelen = field->dcols - (datalen + freelen);

	  if ((result = Insert_String(form, row + 1, split, freelen)) == E_OK)
	    {
	      wmove(form->w, row, datalen);
	      wclrtoeol(form->w);
	      wmove(form->w, row, 0);
	      myINSNSTR(form->w, txt, len);
	      wmove(form->w, row, len);
	      myINSNSTR(form->w, &myBLANK, 1);
	      return E_OK;
	    }
	}
      return (result);
    }
}
