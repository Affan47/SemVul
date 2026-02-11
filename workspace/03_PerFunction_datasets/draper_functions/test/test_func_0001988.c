parse_until_word(machine_t *machine) {
    object_t stop_word;
    object_t parse_stack;
    object_t object;
    stop_word = list_pop(&machine->core.data);
    parse_stack = list_nil;
label_scan_loop:
    if (parse_scan(machine, &object)) {
        if (object_is_word(object)) {
            if (object_eq(stop_word, object))
                goto label_done;
            if (parse_is_parsing_word(object)) {
                object_t sub;
                machine = machine_execute(machine, object);
                sub = list_head(machine->core.data);
                machine->core.data = list_tail(machine->core.data);
                parse_stack = list_append(sub, parse_stack);
                goto label_scan_loop;
            }
        }
        parse_stack = list_new(object, parse_stack);
        goto label_scan_loop;
    }
label_done:
    list_push(&machine->core.data, list_reverse(parse_stack));
    return machine;
}
