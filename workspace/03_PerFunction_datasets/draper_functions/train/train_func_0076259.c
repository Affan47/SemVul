dequeue_int(Queue* q,ScmObj* result){{
#line 496 "./queue.scm"
if (Q_EMPTY_P(q)){return (TRUE);} else {
*(result)=(SCM_CAR(Q_HEAD(q)));
Q_HEAD(q)=(SCM_CDR(Q_HEAD(q)));
--(Q_LENGTH(q));
return (FALSE);}}}
