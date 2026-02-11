success(const vector<const mail::folder *> &folders,
			    bool doSort)
{
	vector<const mail::folder *> cpy=folders;

	if (doSort)
		sort(cpy.begin(), cpy.end(),
		     mail::folder::sort(foldersFirst));

	vector<const mail::folder *>::const_iterator
		b=cpy.begin(),
		e=cpy.end();

	folder_list.clear();
	while (b != e)
	{
		const mail::folder *fptr= *b++;

		folder_list.push_back(fptr->toString());
	}
}
