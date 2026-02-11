HandleRoundFinishedSlot()
  {
    Round *round = qobject_cast<Round *>(sender());
    if(round != _current_round.data()) {
      qWarning() << "Received an awry Round Finished notification";
      return;
    }

    qDebug() << "Session" << ToString() << "round" << _current_round <<
      "finished due to" << _current_round->GetStoppedReason();

    if(!_current_round->Successful()) {
      _trim_send_queue = 0;
    }

    emit RoundFinished(_current_round);

    if(Stopped()) {
      qDebug() << "Session stopped.";
      return;
    }

    HandleRoundFinished();
  }
