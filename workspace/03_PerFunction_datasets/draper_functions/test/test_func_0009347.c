operator++()
  {
    if (!_stack.empty())
      {
        _ptr = _stack.top();
        _stack.pop();
      }
    else
      {
        int next = _notVisited.FirstBit();
        if (next != _notVisited.EndBit())
          {
            _ptr = _parent->GetAtom(next + 1);
            _notVisited.SetBitOff(next);
          }
        else
          _ptr = NULL;
      }

    if (_ptr)
      {
        vector<OBBond*>::iterator i;
        OBAtom *a;

        for (a = _ptr->BeginNbrAtom(i); a; a = _ptr->NextNbrAtom(i))
          if (_notVisited[a->GetIdx() - 1])
            {
              _stack.push(a);
              _notVisited.SetBitOff(a->GetIdx() - 1);
            }
      }

    return *this;
  }
