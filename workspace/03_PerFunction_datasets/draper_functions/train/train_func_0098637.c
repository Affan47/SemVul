dmi_ipmi_interface_type(uint8_t code)
{

    static const char *type[] = {
	"Unknown",
	"KCS (Keyboard Control Style)",
	"SMIC (Server Management Interface Chip)",
	"BT (Block Transfer)",
	"SSIF (SMBus System Interface)"
    };

    if (code <= 0x04)
	return type[code];
    return out_of_spec;
}
