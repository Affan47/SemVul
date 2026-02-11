c_include(void)
{
FILE *nf;
includestr *s;
uschar *t = word;

if (macactive) { error_moan(30); return; }

nextsigch();
while (in_line[chptr] != 0 && in_line[chptr] != ';' &&
       !isspace((int)in_line[chptr]))
 *t++ = in_line[chptr++];
*t = 0;
if (word[0] == 0) { error_moan(29); return; }
nextsigch();
if (in_line[chptr] != ';') error_moan(3);

nf = fopen(CS word, "r");
if (nf == NULL)
  {
  error_moan(1, word, "input", strerror(errno));
  return;
  }

s = getstore(sizeof(includestr));
s->prev = included_from;
s->prevfile = main_input;
included_from = s;

file_line_stack[inc_stack_ptr] = in_line;
file_chptr_stack[inc_stack_ptr++] = chptr;

in_line = getstore(INPUT_LINESIZE);
in_line[0] = ';';
in_line[1] = '\n';
in_line[2] = 0;
chptr = 0;

main_input = nf;
}
