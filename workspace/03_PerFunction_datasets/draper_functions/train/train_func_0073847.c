rw_book_free (BookFile * book)
{
	if (book->bookfilename)
		g_free (book->bookfilename);

	if (book->words.w)
	{
		int i;
		i = 0;
		while (book->words.w[i])
		{
			g_free (book->words.w[i]);
			if (book->words.t[i])
				g_free (book->words.t[i]);
			if (book->words.m[i])
				g_free (book->words.m[i]);
			i++;
		}
		g_free (book->words.w);
		g_free (book->words.t);
		g_free (book->words.m);
	}
	if (book->name)
		g_free (book->name);
	if (book->count)
		g_free (book->count);
	if (book->author)
		g_free (book->author);
	if (book->email)
		g_free (book->email);
	if (book->website)
		g_free (book->website);
	if (book->about)
		g_free (book->about);
}
