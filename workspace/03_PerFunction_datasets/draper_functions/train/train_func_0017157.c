adc_enqueue_request(struct pcf50633 *pcf, struct pcf50633_adc_request *req)
{
	struct pcf50633_adc *adc = __to_adc(pcf);
	int head, tail;

	mutex_lock(&adc->queue_mutex);

	head = adc->queue_head;
	tail = adc->queue_tail;

	if (adc->queue[tail]) {
		mutex_unlock(&adc->queue_mutex);
		dev_err(pcf->dev, "ADC queue is full, dropping request\n");
		return -EBUSY;
	}

	adc->queue[tail] = req;
	if (head == tail)
		trigger_next_adc_job_if_any(pcf);
	adc->queue_tail = (tail + 1) & (PCF50633_MAX_ADC_FIFO_DEPTH - 1);

	mutex_unlock(&adc->queue_mutex);

	return 0;
}
