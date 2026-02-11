PopulateOrExchange(ShuttleGui & S)
{
   S.SetBorder(2);

   S.StartStatic(_("When importing audio files"));
   {
      S.StartRadioButtonGroup(wxT("/FileFormats/CopyOrEditUncompressedData"), wxT("copy"));
      {
         S.TieRadioButton(_("&Make a copy of uncompressed audio files before editing (safer)"),
                          wxT("copy"));
         S.TieRadioButton(_("&Read uncompressed audio files directly from the original (faster)"),
                          wxT("edit"));
      }
      S.EndRadioButtonGroup();

      S.TieCheckBox(_("&Normalize all tracks in project"),
                    wxT("/AudioFiles/NormalizeOnLoad"),
                    false);
   }
   S.EndStatic();

   S.StartStatic(_("When exporting tracks to an audio file"));
   {
      S.StartRadioButtonGroup(wxT("/FileFormats/ExportDownMix"), true);
      {
         S.TieRadioButton(_("&Always mix all tracks down to Stereo or Mono channel(s)"),
                          true);
         S.TieRadioButton(_("&Use custom mix (for example to export a 5.1 multichannel file)"),
                          false);
      }
      S.EndRadioButtonGroup();

      S.TieCheckBox(_("S&how Metadata Editor prior to export step"),
                    wxT("/AudioFiles/ShowId3Dialog"),
                    true);


   }
   S.EndStatic();
#ifdef USE_MIDI
   S.StartStatic(_("When exporting track to an Allegro (.gro) file"));
   {
      S.StartRadioButtonGroup(wxT("/FileFormats/AllegroStyle"), true);
      {
         S.TieRadioButton(_("Represent times and durations in &seconds"),
                          true);
         S.TieRadioButton(_("Represent times and durations in &beats"),
                          false);
      }
      S.EndRadioButtonGroup();
   }
   S.EndStatic();
#endif
}
