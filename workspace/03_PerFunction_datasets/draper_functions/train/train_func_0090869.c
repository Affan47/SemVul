FE_Insert_Line(FORM * form)
{
  FIELD *field = form->current;
  int result = E_REQUEST_DENIED;

  if (Check_Char(field->type,(int)C_BLANK,(TypeArgument *)(field->arg)))
    {
      bool Maybe_Done = (form->currow!=(field->drows-1)) &&
                        Is_There_Room_For_A_Line(form);

      if (!Single_Line_Field(field) &&
          (Maybe_Done || Growable(field)))
        {
          if (!Maybe_Done && !Field_Grown(field,1))
            result = E_SYSTEM_ERROR;
          else
            {
              form->curcol = 0;
              winsertln(form->w);
              result = E_OK;
            }
        }
    }
  return result;
}
