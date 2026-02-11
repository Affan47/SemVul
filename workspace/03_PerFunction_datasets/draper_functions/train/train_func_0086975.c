convert_content(struct content *content, List *request_headers,
                           int allow_empty)
{
    Octstr *new_body;
    int failed = 0;
    int i;

    for (i = 0; i < NUM_CONVERTERS; i++) {
        if (octstr_str_compare(content->type, converters[i].type) == 0 &&
            !http_type_accepted(request_headers, octstr_get_cstr(content->type))) {
            debug("wap.convert",0,"WSP: Converting from <%s> to <%s>",
                  octstr_get_cstr(content->type), converters[i].result_type);


            if (allow_empty && octstr_len(content->body) == 0)
                return 1;

            new_body = converters[i].convert(content);
            if (new_body != NULL) {
                long s = octstr_len(content->body);
                octstr_destroy(content->body);
                octstr_destroy(content->type);
                content->body = new_body;
                content->type = octstr_create(converters[i].result_type);
                debug("wap.convert",0,"WSP: Content-type is "
                      "now <%s>, size %ld bytes (before: %ld bytes), content body is:",
                      converters[i].result_type, octstr_len(new_body), s);
                octstr_dump(new_body, 0);
                return 1;
            }
            debug("wap.convert",0,"WSP: Content convertion failed!");
            failed = 1;
        }
    }

    return (failed ? -1 : 0);
}
