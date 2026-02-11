ParseSection( ifstream &in, const string *opt, unsigned long &line ) {
  int rc = KeyValueSectionHandler::ParseSection( in, opt, line );

  if ( rc == 0 ) {
    for ( vector<pair<string, string> >::iterator it = pairs.begin();
          it != pairs.end(); ++it ) {
      string key = (*it).first;
      string val = (*it).second;

      if ( key == "mapwidth" ) mapsize.x = StrToNum(val);
      else if ( key == "mapheight" ) mapsize.y = StrToNum(val);
      else if ( key == "name" ) m.SetName(StrToNum(val));
      else if ( key == "info" ) m.SetLevelInfoMsg(StrToNum(val));
      else if ( key == "campaignname" ) m.SetCampaignName(StrToNum(val));
      else if ( key == "campaigninfo" ) m.SetCampaignInfo(StrToNum(val));
      else if ( key == "players" ) m.SetNumPlayers(StrToNum(val));
      else if ( key == "unitset" ) units = val;
      else if ( key == "tileset" ) tiles = val;
      else if ( key == "nextmap" ) m.SetSequel(val.c_str());
      else if ( key == "music" ) m.SetMusic(val.c_str());
      else if ( key == "campaign" ) m.SetCampaign(StrToNum(val) != 0);
      else if ( key == "skirmish" ) m.SetSkirmish(StrToNum(val) != 0);
      else {
        rc = 1;
        cerr << "Error near line " << line << ": Invalid keyword '" << key << "'" << endl;
        break;
      }
    }
  }

  return rc;
}
