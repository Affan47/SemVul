session_compare_question(dns_msg_question_t *a, dns_msg_question_t *b)
{
    if (a->mq_type != DNS_TYPE_ALL && b->mq_type != DNS_TYPE_ALL) {
        if (a->mq_type != b->mq_type)
            return -1;
    }

    if (a->mq_class != DNS_CLASS_ANY && b->mq_type != DNS_CLASS_ANY) {
        if (a->mq_class != b->mq_class)
            return -1;
    }

    return strcasecmp(a->mq_name, b->mq_name);
}
