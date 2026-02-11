Backtrack(State &state)
      {
        if (DEBUG)
          cout << red << "backtrack... " << normal << state.queryPath.size()-1 << endl;

        if (state.queryPath.size()) {
          state.mapping[state.queryPath.back()] = 0;
          state.queryPathBits.SetBitOff(state.queryPath.back());
          state.queryPath.pop_back();
        }
        if (state.queriedPath.size()) {
          state.queriedPathBits.SetBitOff(state.queriedPath.back());
          state.queriedPath.pop_back();
        }

        unsigned int depth = state.queryPath.size() + 1;
        std::replace(state.queryDepths.begin(), state.queryDepths.end(), depth, static_cast<unsigned int>(0));
        std::replace(state.queriedDepths.begin(), state.queriedDepths.end(), depth, static_cast<unsigned int>(0));
      }
