sessionKey() const
{
	return "views/" + QString::number(lyxview_->id())
		+ "/" + name();
}
