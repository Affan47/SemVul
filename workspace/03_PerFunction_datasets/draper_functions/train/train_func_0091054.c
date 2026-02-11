saveView() const {
  saveSettings("window");
  if (source) {
    getApp()->reg().writeStringEntry("window","source-list-current",source->settingKey().text());
    }
  }
