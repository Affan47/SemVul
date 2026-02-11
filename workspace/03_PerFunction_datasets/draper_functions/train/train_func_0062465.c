VSC_Generic(FORM *form, int lines)
{
  FIELD *field = form->current;
  int res = E_REQUEST_DENIED;
  int rows_to_go = (lines > 0 ? lines : -lines);

  if (lines > 0)
    {
      if ( (rows_to_go + form->toprow) > (field->drows - field->rows) )
        rows_to_go = (field->drows - field->rows - form->toprow);

      if (rows_to_go > 0)
        {
          form->currow += rows_to_go;
          form->toprow += rows_to_go;
          res = E_OK;
        }
    }
  else
    {
      if (rows_to_go > form->toprow)
        rows_to_go = form->toprow;

      if (rows_to_go > 0)
        {
          form->currow -= rows_to_go;
          form->toprow -= rows_to_go;
          res = E_OK;
        }
    }
  return(res);
}
