version(std::ostream& os) const
{
    bool  b64    = sizeof(void*)==8;
    const char* sBuild = b64 ? "(64 bit build)" : "(32 bit build)" ;
    os << EXV_PACKAGE_STRING << " " << Exiv2::versionNumberHexString() << " " << sBuild << "\n"
       << _("Copyright (C) 2004-2012 Andreas Huggel.\n")
       << "\n"
       << _("This program is free software; you can redistribute it and/or\n"
            "modify it under the terms of the GNU General Public License\n"
            "as published by the Free Software Foundation; either version 2\n"
            "of the License, or (at your option) any later version.\n")
       << "\n"
       << _("This program is distributed in the hope that it will be useful,\n"
            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
            "GNU General Public License for more details.\n")
       << "\n"
       << _("You should have received a copy of the GNU General Public\n"
            "License along with this program; if not, write to the Free\n"
            "Software Foundation, Inc., 51 Franklin Street, Fifth Floor,\n"
            "Boston, MA 02110-1301 USA\n");
}
