execute(CMD_Args *args, CMD_Context context) {
        if (args == NULL)
            args = new CMD_Args();

        switch (context) {
        case 0:
            args->set_string_arg("ui-dialog-title", _("Save profiles?"));
            args->set_string_arg("ui-dialog-text",
                               _("Some profiles were changed!\n\n"
                                 "'Yes' will save changes to disk, 'No' will reject all changes.\n"
                                 "'Cancel': will allow to continue editing."));
            args->set_string_arg("ui-dialog-text-arg", "filename");
            args->add_callback("ui-dialog-cancel-CB", this, 1);
            args->add_callback("ui-dialog-yes-no-CB-no", this, 2);
            args->add_callback("ui-dialog-yes-no-CB-yes", this, 3);
            CMD_EXEC_ARGS("ui-dialog-yes-no-cancel", args);
            break;
        case 1:
            break;
        case 2:
            _w->reject();
            break;
        case 3:
            _w->save();
            break;
        }
    }
}
