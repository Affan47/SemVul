make_up(const Line &line, Area::size_type w, int halign)
{


  if (line.empty()) return 0;

  auto_ptr<Area> res(new Area);

  Line::size_type from = 0;

  while (from < line.length()) {


    if (line[from].character == '\n') {
      res->resize(res->width(), res->height() + 1);
      from++;
      continue;
    }

    Line::size_type to = from + 1;
    int to_from;

    Line::size_type lbp = (Line::size_type) -1;


    while (to < line.length()) {
      if (line[to].character == '\n') {
        break;
      }
      char c1 = line[to].character, c2 = line[to - 1].character;
      if (c1 == ' ' || c1 == '(' || c1 == '[' || c1 == '{' || (
        (
          c2 == '-' ||
          c2 == '/' ||
          c2 == ':'
        ) &&
        c1 != ',' &&
        c1 != '.' &&
        c1 != ';' &&
        c1 != ':'
      )) {
        lbp = to++;
        while (to < line.length() && line[to].character == ' ') to++;
      } else {
        to++;
      }

      if (line.utf_length(from,to) > w && lbp != (Area::size_type) -1)
                    { to = lbp; break; }
    }

    to_from = line.utf_length(from,to);


    Area::size_type x = 0;
    Area::size_type len = to - from;
    if (halign == Area::LEFT || to_from >= w) { ;                   } else
    if (halign == Area::CENTER)           { x += (w - to_from) / 2; } else
    if (halign == Area::RIGHT)            { x += w - to_from;       }
    res->insert(line.cells() + from, len, x, res->height());


    if (to == line.length()) break;

    from = to;
    if (line[from].character == '\n') {
      ++from;
    } else
    if (line[from].character == ' ') {
      do {
        ++from;
      } while (from < line.length() && line[from].character == ' ');
    }
  }

  return res.release();
}
