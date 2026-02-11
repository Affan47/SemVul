DrawRingBond(OBAtom *beginAtom, OBAtom *endAtom, const vector3 &center, int order)
  {
    if (order != 2) {
      DrawSimpleBond(beginAtom, endAtom, order);
      return;
    }

    vector3 begin = beginAtom->GetVector();
    vector3 end = endAtom->GetVector();

    vector3 vb = (end - begin).normalize();
    vector3 orthogonalLine = cross(vb, VZ);
    vector3 spacing = orthogonalLine * bondSpacing * 1.2;
    vector3 offset = vb * bondSpacing;
    if ((begin + spacing - center).length() > (begin - spacing - center).length())
      spacing *= -1.0;

    vector3 vbb = end - begin;
    if (HasLabel(beginAtom))
      begin += 0.33 * vbb;
    if (HasLabel(endAtom))
      end -= 0.33 * vbb;
    painter->DrawLine(begin.x(), begin.y(), end.x(), end.y());

    if (HasLabel(beginAtom))
      begin -= 0.10 * vbb;
    if (HasLabel(endAtom))
      end += 0.10 * vbb;
    painter->DrawLine(begin.x() + spacing.x() + offset.x(), begin.y() + spacing.y() + offset.y(),
                      end.x() + spacing.x() - offset.x(), end.y() + spacing.y() - offset.y());
  }
