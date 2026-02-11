generateInput (Tree sig, const string& idx)
{
	return generateCacheCode(sig, subst("$1input$0[i]", idx, icast()));
}
