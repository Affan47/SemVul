post_form(FORM * form)
{
  WINDOW *formwin;
  int err;
  int page;

  if (!form)
    RETURN(E_BAD_ARGUMENT);

  if (form->status & _POSTED)
    RETURN(E_POSTED);

  if (!(form->field))
    RETURN(E_NOT_CONNECTED);

  formwin = Get_Form_Window(form);
  if ((form->cols > getmaxx(formwin)) || (form->rows > getmaxy(formwin)))
    RETURN(E_NO_ROOM);


  page = form->curpage;
  form->curpage = -1;
  if ((err = _nc_Set_Form_Page(form,page,form->current))!=E_OK)
    RETURN(err);

  form->status |= _POSTED;

  Call_Hook(form,forminit);
  Call_Hook(form,fieldinit);

  _nc_Refresh_Current_Field(form);
  RETURN(E_OK);
}
