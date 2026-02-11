identify_altar_type_move_on(ob_methods *context, object *altar, object *money, object *originator) {
    object *marked;
    int success = 0;
    char desc[MAX_BUF];

    if (common_pre_ob_move_on(altar, money, originator) == METHOD_ERROR)
        return METHOD_OK;

    if (originator == NULL || originator->type != PLAYER) {
        common_post_ob_move_on(altar, money, originator);
        return METHOD_OK;
    }


    if (money->type != MONEY || !check_altar_sacrifice(altar, money, 0, NULL)) {
        common_post_ob_move_on(altar, money, originator);
        return METHOD_OK;
    }
    marked = find_marked_object(originator);


    if (marked
    && !QUERY_FLAG(marked, FLAG_IDENTIFIED)
    && need_identify(marked)) {
        if (operate_altar(altar, &money)) {
            marked = identify(marked);
            draw_ext_info_format(NDI_UNIQUE, 0, originator, MSG_TYPE_APPLY, MSG_TYPE_APPLY_SUCCESS,
                "You have %s.",
                ob_describe(marked, originator, desc, sizeof(desc)));

            if (marked->msg) {
                draw_ext_info(NDI_UNIQUE, 0, originator, MSG_TYPE_APPLY, MSG_TYPE_APPLY_SUCCESS,
                    "The item has a story:");
                draw_ext_info(NDI_UNIQUE, 0, originator, MSG_TYPE_APPLY, MSG_TYPE_APPLY_SUCCESS,
                    marked->msg);
            }
            common_post_ob_move_on(altar, money, originator);
            return METHOD_OK;
        }
    }

    FOR_INV_PREPARE(originator, id) {
        if (!QUERY_FLAG(id, FLAG_IDENTIFIED)
        && !id->invisible
        && need_identify(id)) {
            if (operate_altar(altar, &money)) {
                id = identify(id);
                draw_ext_info_format(NDI_UNIQUE, 0, originator, MSG_TYPE_APPLY, MSG_TYPE_APPLY_SUCCESS,
                    "You have %s.", ob_describe(id, originator, desc, sizeof(desc)));
                if (id->msg) {
                    draw_ext_info(NDI_UNIQUE, 0, originator, MSG_TYPE_APPLY, MSG_TYPE_APPLY_SUCCESS,
                        "The item has a story:");
                    draw_ext_info(NDI_UNIQUE, 0, originator, MSG_TYPE_APPLY, MSG_TYPE_APPLY_SUCCESS,
                        id->msg);
                }
                success = 1;

                if (money == NULL || !check_altar_sacrifice(altar, money, 0, NULL))
                    break;
            } else {
                LOG(llevError, "check_id_altar:  Couldn't do sacrifice when we should have been able to\n");
                break;
            }
        }
    } FOR_INV_FINISH();
    if (!success)
        draw_ext_info(NDI_UNIQUE, 0, originator, MSG_TYPE_APPLY, MSG_TYPE_APPLY_FAILURE,
            "You have nothing that needs identifying");
    common_post_ob_move_on(altar, money, originator);
    return METHOD_OK;
}
