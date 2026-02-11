mwi_received_in_main (const std::string aor,
					   const std::string info)
{
  if (boost::shared_ptr<Opal::Bank> bk = bank.lock ()) {

    AccountPtr account = bk->find_account (aor);

    if (account) {

      account->handle_message_waiting_information (info);
    }
  }
}
