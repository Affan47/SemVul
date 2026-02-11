categoryEnd()
{
	mIndent = mIndent.left( mIndent.length() - INDENT.length() );

	mCategories.pop();

	mTabStack.pop();
}
