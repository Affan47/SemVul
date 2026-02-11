sty_line(VOID)
{
typedef enum{FROM_INI,FROM_LOCAL,FROM_CMD_LINE}STYLE_MODE;

static STYLE_MODE mode= FROM_INI;

from_sprm= BOOLEAN(mode==FROM_INI||mode==FROM_CMD_LINE);

switch(mode)
{
case FROM_INI:
if(!sty0_line(sprm_ptr0))
mode++;
else
return YES;

case FROM_LOCAL:
if(!sty0_line(NULL))
mode++;
else
return YES;

case FROM_CMD_LINE:
return sty0_line(sprm_end);
}

return YES;
}
