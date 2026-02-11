count_statistics(IndexWriter *writer) {
    IndexBuffer *tmp;
    int i;

    writer->strings_lcps_compressed=0;
    for(tmp=writer->sorted_buffers;tmp;tmp=tmp->next) {
	writer->strings_lcps_compressed+=tmp->lcp;
    }


    if (writer->file_list) {
	const char *name;

	writer->flist_size=4;
	for(i=0;i<flist_files(writer->file_list);i++) {
	    name=flist_name(writer->file_list,i);
	    writer->flist_size+=4;
	    if (name!=NULL) {
		writer->flist_size+=strlen(name)+1;
	    }
	    writer->flist_size+=4;
	}
    } else {
	writer->flist_size=0;
    }


    writer->total_index_file_size=1024+
	writer->terms*4+
	writer->total_string_bytes-writer->strings_lcps_compressed+
	writer->terms+
	(writer->total_postings_bytes+writer->terms);
    writer->flist_start=writer->total_index_file_size;
    writer->total_index_file_size+=writer->flist_size;
}
