print_span(struct span *span) {
    if (span == NULL)
        return;
    printf("%s label=(%i:%i) value=(%i:%i) span=(%i,%i)\n",
            span->filename->str,
            span->label_start, span->label_end,
            span->value_start, span->value_end,
            span->span_start, span->span_end);
}
