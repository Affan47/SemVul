addComment(const char *comment)
{
	Comment *newdata = new Comment(comment);
	d_allDataVector.push_back(newdata);
}
