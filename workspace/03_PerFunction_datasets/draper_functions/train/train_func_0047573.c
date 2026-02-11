showobject(int num)
{
	pdf_obj *obj;

	if (!doc)
		fz_throw(ctx, "no file specified");

	obj = pdf_load_object(doc, num, 0);

	if (isimage(obj))
		saveimage(num);
	else if (isfontdesc(obj))
		savefont(obj, num);

	pdf_drop_obj(obj);
}
