getNthClip(int index)
      {
        const std::string name = _descriptor->getClipsByOrder()[index]->getName();
        return _clips[name];
      }
