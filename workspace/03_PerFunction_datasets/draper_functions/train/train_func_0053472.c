set_design(CWIDGET *_object)
{
	CWIDGET *cont;

	if (GB.Is(THIS, CLASS_UserControl))
		set_design_recursive(WIDGET);
	else if (!GB.Is(THIS, CLASS_Container))
		set_design_object(THIS);

	CWIDGET_set_flag(THIS, WF_DESIGN_LEADER);

	if (GB.Is(THIS, CLASS_Container))
	{


		cont = CWidget::get(QCONTAINER(THIS));

		if (cont && cont != THIS)
			set_design_object(cont);
	}

	if (GB.Is(THIS, CLASS_TabStrip))
	{
		THIS->flag.fillBackground = TRUE;
		CWIDGET_reset_color(THIS);
	}
}
