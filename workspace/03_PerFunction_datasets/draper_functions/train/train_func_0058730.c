paramsToDialog(Inset const * inset)
{
	InsetLabel const * label = static_cast<InsetLabel const *>(inset);
	InsetCommandParams const & params = label->params();
	keywordED->setText(toqstr(params["name"]));
}
