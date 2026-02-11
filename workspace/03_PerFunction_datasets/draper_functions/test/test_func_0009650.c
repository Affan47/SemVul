configure(Vector<String> &conf, ErrorHandler *errh)
{
    unsigned target_q, max_p, stability = 4;
    String queues_string = String();
    if (Args(conf, this, errh)
	.read_mp("TARGET", target_q)
	.read_mp("MAX_P", FixedPointArg(16), max_p)
	.read("QUEUES", AnyArg(), queues_string)
	.read("STABILITY", stability)
	.complete() < 0)
	return -1;
    if (target_q < 10)
	target_q = 10;
    unsigned min_thresh = target_q / 2;
    unsigned max_thresh = target_q + min_thresh;
    return finish_configure(min_thresh, max_thresh, true, max_p, stability, queues_string, errh);
}
