write_samples(void* target_buffer,
				  long int samples)
{
  if (is_running() != true) {


    timeradd(&data_processed_rep, &buffer_length_rep, &data_processed_rep);
  }
  else {

    block_until_data_available();


    timeradd(&data_processed_rep, &buffer_length_rep, &data_processed_rep);
  }
}
