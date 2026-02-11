dispatchParams()
{
	std::string const lfun = InsetCommand::params2string(params_);
	dispatch(FuncRequest(getLfun(), lfun));
}
