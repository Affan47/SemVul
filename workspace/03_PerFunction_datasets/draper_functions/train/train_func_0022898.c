fi_shrink(struct frame_index *fi)
{
	if(fi->fill < 2) return;
	else
	{
		size_t c;
		debug2("shrink index with fill %lu and step %lu", (unsigned long)fi->fill, (unsigned long)fi->step);
		fi->step *= 2;
		fi->fill /= 2;

		for(c = 0; c < fi->fill; ++c)
		fi->data[c] = fi->data[2*c];
	}

	fi->next = fi_next(fi);
}
