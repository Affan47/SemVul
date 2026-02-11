dict_serialized_length_old (dict_t *this)
{

        if (!this) {
                gf_log_callingfn ("dict", GF_LOG_WARNING, "dict is NULL");
                return -1;
        }

        int32_t len = 9;
        int32_t count = this->count;
        data_pair_t *pair = this->members_list;

        while (count) {
                len += 18;
                len += strlen (pair->key) + 1;
                if (pair->value->vec) {
                        int i;
                        for (i=0; i<pair->value->len; i++) {
                                len += pair->value->vec[i].iov_len;
                        }
                } else {
                        len += pair->value->len;
                }
                pair = pair->next;
                count--;
        }

        return len;
}
