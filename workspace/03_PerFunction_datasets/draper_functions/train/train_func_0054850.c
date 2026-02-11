transport_type_process(ob_methods *context, object *op) {


    if (op->speed_left < 0.0) {
        op->speed_left += 1.0;
        return 1;
    }
    return 0;
}
