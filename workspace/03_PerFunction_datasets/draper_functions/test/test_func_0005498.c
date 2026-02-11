set_current_field(FORM  * form, FIELD * field)
{
  int err = E_OK;

  if ( !form || !field )
    RETURN(E_BAD_ARGUMENT);

  if ( (form != field->form) || Field_Is_Not_Selectable(field) )
    RETURN(E_REQUEST_DENIED);

  if (!(form->status & _POSTED))
    {
      form->current = field;
      form->curpage = field->page;
  }
  else
    {
      if (form->status & _IN_DRIVER)
	err = E_BAD_STATE;
      else
	{
	  if (form->current != field)
	    {
	      if (!_nc_Internal_Validation(form))
	       err = E_INVALID_FIELD;
	      else
		{
		  Call_Hook(form,fieldterm);
		  if (field->page != form->curpage)
		    {
		      Call_Hook(form,formterm);
		      err = _nc_Set_Form_Page(form,field->page,field);
		      Call_Hook(form,forminit);
		    }
		  else
		    {
		      err = _nc_Set_Current_Field(form,field);
		    }
		  Call_Hook(form,fieldinit);
		  _nc_Refresh_Current_Field(form);
		}
	    }
	}
    }
  RETURN(err);
}
