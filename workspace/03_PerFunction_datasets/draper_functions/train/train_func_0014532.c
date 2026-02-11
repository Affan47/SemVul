GetResourceTypeAndSize(Widget w, String resource_name,
				   XrmQuark *type, Cardinal *size)
#else
static void GetResourceTypeAndSize(w, resource_name, type, size)
Widget w;
String resource_name;
XrmQuark *type;
Cardinal *size;
#endif
{
    int i;
    Boolean found = False;
    WidgetClass c = XtClass(w);
    XtResourceList *list = (XtResourceList *) c->core_class.resources;
    XrmQuark name = XrmStringToQuark(resource_name);


    for(i=0; i < c->core_class.num_resources; i++) {
	if ((list[i] != NULL) &&
	    ((XrmName)list[i]->resource_name == name)) {
	    found = True;
	    break;
	}
    }


    if (!found && XtParent(w) && XtIsConstraint(XtParent(w))) {
	ConstraintWidgetClass c =
	    (ConstraintWidgetClass) XtClass(XtParent(w));
	list = (XtResourceList *) c->constraint_class.resources;
	for(i = 0; i < c->constraint_class.num_resources; i++) {
	    if ((list[i] != NULL) &&
		((XrmName)list[i]->resource_name == name)) {
		found = True;
		break;
	    }
	}
    }

    if (found) {
	*type = (XrmQuark)list[i]->resource_type;
	*size = list[i]->resource_size;
    }
}
