newInset()
{
	docstring const argument = d->widget_->dialogToParams();
	dispatch(FuncRequest(d->widget_->creationCode(), argument));
}
