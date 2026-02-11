http_header_pack(List *headers)
{
    Octstr *name, *value;
    Octstr *name2, *value2;
    long i, j;

    gwlib_assert_init();
    gw_assert(headers != NULL);


    for(i = 0; i < gwlist_len(headers); i++) {
        http_header_get(headers, i, &name, &value);


        for(j=i+1; j < gwlist_len(headers); j++) {
            http_header_get(headers, j, &name2, &value2);

            if(octstr_case_compare(name, name2) == 0) {
                if(octstr_len(value) + 2 + octstr_len(value2) > MAX_HEADER_LENGTH) {
		    octstr_destroy(name2);
		    octstr_destroy(value2);
                    break;
                } else {
		    Octstr *header;


		    header = gwlist_get(headers, i);
		    octstr_destroy(header);
                    gwlist_delete(headers, i, 1);


                    octstr_append(value, octstr_imm(", "));
                    octstr_append(value, value2);

		    header = octstr_create("");
                    octstr_append(header, name);
                    octstr_append(header, octstr_imm(": "));
                    octstr_append(header, value);
                    gwlist_insert(headers, i, header);


		    header = gwlist_get(headers, j);
		    octstr_destroy(header);
                    gwlist_delete(headers, j, 1);
                    j--;
                }
            }
	    octstr_destroy(name2);
	    octstr_destroy(value2);
        }
	octstr_destroy(name);
	octstr_destroy(value);
    }
}
