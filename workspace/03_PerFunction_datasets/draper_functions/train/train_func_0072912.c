applyOptions()
{
	Q3PtrListIterator<OptionsTab> it(tabs);
	for ( ; it.current(); ++it) {
		it.current()->applyOptions();
	}
}
