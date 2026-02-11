set_lang_hook(Config & c) {
    set_file_encoding(lang()->data_encoding(), c);
    word_lookup.reset(new WordLookup(10, Hash(lang()), Equal(lang())));
    use_soundslike = lang()->have_soundslike();
  }
}
