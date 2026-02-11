redisplay(void)
{
  boolean done = false;
  waswritten = false;
  do {
    fprintf(stderr, "NEXT (R # + - S . T U W O F H J K L C ? X Q) ");
    fprintf(stderr, "(? for Help): ");
#ifdef WIN32
    phyFillScreenColor();
#endif
    fflush(stdout);
    scanf("%c%*[^\n]", &ch);
    getchar();
    uppercase(&ch);
    if (strchr("HJKLCFORSTUXQ+#-.W?",ch) != NULL){
      switch (ch) {

      case 'R':
        rearrange();
        break;

      case '#':
        dnamove_nextinc();
        break;

      case '+':
        dnamove_nextchar();
        break;

      case '-':
        dnamove_prevchar();
        break;

      case 'S':
        dnamove_show();
        break;

      case '.':
        dnamove_printree();
        break;

      case 'T':
        try();
        break;

      case 'U':
        undo();
        break;

      case 'W':
        treewrite(done);
        break;

      case 'O':
        changeoutgroup();
        break;

      case 'F':
        flip(0);
        break;

      case 'H':
        window(left, &leftedge, &topedge, hscroll, vscroll, treelines,
                 screenlines, screenwidth, farthest, subtree);
        dnamove_printree();
        break;

      case 'J':
        window(downn, &leftedge, &topedge, hscroll, vscroll, treelines,
                 screenlines, screenwidth, farthest, subtree);
        dnamove_printree();
        break;

      case 'K':
        window(upp, &leftedge, &topedge, hscroll, vscroll, treelines,
                 screenlines, screenwidth, farthest, subtree);
        dnamove_printree();
        break;

      case 'L':
        window(right, &leftedge, &topedge, hscroll, vscroll, treelines,
                 screenlines, screenwidth, farthest, subtree);
        dnamove_printree();
        break;

      case 'C':
        clade();
        break;

      case '?':
        help("site");
        dnamove_printree();
        break;

      case 'X':
        done = true;
        break;

      case 'Q':
        done = true;
        break;
      }
    }
  } while (!done);
  if (written)
    return;
  do {
    fprintf(stderr, "Do you want to write out the tree to a file? (Y or N): ");
#ifdef WIN32
    phyFillScreenColor();
#endif
    fflush(stdout);
    scanf("%c%*[^\n]", &ch);
    getchar();
    if (ch == 'Y' || ch == 'y')
      treewrite(done);
  } while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
}
