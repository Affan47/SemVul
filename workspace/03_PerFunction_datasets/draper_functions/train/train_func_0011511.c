queue_regulatory_request(struct regulatory_request *request)
{
	if (isalpha(request->alpha2[0]))
		request->alpha2[0] = toupper(request->alpha2[0]);
	if (isalpha(request->alpha2[1]))
		request->alpha2[1] = toupper(request->alpha2[1]);


	spin_lock(&reg_requests_lock);
	reglib_queue_request(request);
	spin_unlock(&reg_requests_lock);

	schedule_work(&reg_work);
}
