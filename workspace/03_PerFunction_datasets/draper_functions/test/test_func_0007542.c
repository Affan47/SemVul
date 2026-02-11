ParseLine(const char* line)
  {
    static SpaceGroup *group = NULL;
    static int step = SPACE_GROUP_ID;
    static string HMs;
    switch (step)
      {
      case SPACE_GROUP_ID:
        group = new SpaceGroup();
        group->SetId(atoi (line));
        step++;
        break;
      case SPACE_GROUP_HALL:
        group->SetHallName(line);
        step++;
        break;
      case SPACE_GROUP_HM:
        {
          std::string linestr=std::string(line);
          std::string::size_type idx=linestr.find(',');
          if (idx != std::string::npos)
            {
              std::string alt = linestr.substr(0, idx);
              if (alt.length() > 0 && _SpaceGroups.sgbn[alt] == NULL)
                _SpaceGroups.sgbn[alt] = group;
              std::string stripped_HM=RemoveWhiteSpaceUnderscore(alt);
              if (stripped_HM.length() > 0 && _SpaceGroups.sgbn[stripped_HM] == NULL)
                _SpaceGroups.sgbn[stripped_HM] = group;
              group->SetHMName(linestr.substr(idx+1));
            }
          else
            group->SetHMName(line);
          step++;
          break;
        }
      case SPACE_GROUP_TRANSFORM:
        if (strlen(line) == 0)
          {
            step = SPACE_GROUP_ID;
            if (HMs.length() > 0)
              group->RegisterSpaceGroup(1, HMs.c_str());
            else
              group->RegisterSpaceGroup();
            group = NULL;
            HMs.clear();
		      }
        else
          group->AddTransform(line);
        break;
      }
  }
