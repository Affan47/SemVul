OnSessionState(BaseSession* base_session,
                                        BaseSession::State state) {


  Session* session = static_cast<Session*>(base_session);

  if (state == Session::STATE_RECEIVEDINITIATE) {


    const SessionDescription* offer = session->remote_description();
    const SessionDescription* accept = CreateAnswer(offer, CallOptions());
    const ContentInfo* audio_content = GetFirstAudioContent(accept);
    const AudioContentDescription* audio_accept = (!audio_content) ? NULL :
        static_cast<const AudioContentDescription*>(audio_content->description);


    Call *call = CreateCall();
    session_map_[session->id()] = call;
    call->IncomingSession(session, offer);

    if (!audio_accept || audio_accept->codecs().size() == 0) {
      session->Reject(STR_TERMINATE_INCOMPATIBLE_PARAMETERS);
    }
    delete accept;
  }
}
