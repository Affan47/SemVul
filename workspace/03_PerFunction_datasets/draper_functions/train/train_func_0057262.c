_ufnumber_array_object_event(UFObject *object, UFEventType type)
    {
        _UFWidgetData *data = static_cast<_UFWidgetData *>(object->UserData());
        if (type == uf_destroyed) {
            delete data;
            return;
        }
        UFNumberArray &array = *object;
        for (int i = 0; i < array.Size(); i++)
            gtk_adjustment_set_value(data->adjustment(i), array.DoubleValue(i));
        _ufobject_reset_button_state(object);
    }
