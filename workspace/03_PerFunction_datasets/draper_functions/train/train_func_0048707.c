sheet_widget_list_base_set_links (SheetObject *so,
				  GnmExprTop const *output,
				  GnmExprTop const *content)
{
	SheetWidgetListBase *swl = GNM_SOW_LIST_BASE (so);
	dependent_set_expr (&swl->output_dep, output);
	if (NULL != output)
		dependent_link (&swl->output_dep);
	dependent_set_expr (&swl->content_dep, content);
	if (NULL != content)
		dependent_link (&swl->content_dep);
	list_content_eval (&swl->content_dep);
}
