gtksharp_container_invoke_set_child_property (GtkContainerClass *class_struct, GtkContainer* inst, GtkWidget* child, guint property_id, const GValue* value, GParamSpec* pspec)
{
	if (class_struct->set_child_property)
		(* class_struct->set_child_property) (inst, child, property_id, value, pspec);
}
