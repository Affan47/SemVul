MyTriggerNotifyHandler(IMTriggerNotifyStruct *call_data)
{


    if (call_data->flag == 0) {

        if ((call_data->key_index == 0 && hime_im_toggle_keys==Control_Space) ||
            (call_data->key_index == 3 && hime_im_toggle_keys==Shift_Space) ||
            (call_data->key_index == 6 && hime_im_toggle_keys==Alt_Space) ||
            (call_data->key_index == 9 && hime_im_toggle_keys==Windows_Space)
            ) {
            toggle_im_enabled();
        }
        return True;
    } else {

        return False;
    }
}
