XmtRegisterPopupConstructor(StringConst name,
				 XmtWidgetConstructor constructor)
#else
void XmtRegisterPopupConstructor(name, constructor)
StringConst name;
XmtWidgetConstructor constructor;
#endif
{
    XmtWidgetType *t = XtNew(XmtWidgetType);

    if (widget_type_table == NULL) widget_type_table = XmtHashTableCreate(5);

    t->name = (String) name;
    t->wclass = NULL;
    t->constructor = constructor;
    t->set_value_proc = NULL;
    t->get_value_proc = NULL;
    t->popup = True;

    XmtHashTableStore(widget_type_table,
		      (XtPointer)XrmPermStringToQuark(name),
		      (XtPointer)t);
}
