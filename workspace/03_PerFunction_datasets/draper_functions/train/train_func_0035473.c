CreateSoundclip() {
  talk_base::TypedMessageData<Soundclip*> data(NULL);
  Send(MSG_CREATESOUNDCLIP, &data);
  return data.data();
}
