request_start(void)
{

  DBC_REQUIRE(status() != engine_status_running);


  ECA_LOG_MSG(ECA_LOGGER::user_objects, "Request start");


  driver_repp->start();
}
