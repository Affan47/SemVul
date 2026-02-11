configuration_editor_about_cb (ConfigurationEditor* self) {
	gchar* _tmp0_;
	gchar** _tmp1_ = NULL;
	gchar** authors;
	gint authors_length1;
	gint _authors_size_;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_;
	gchar* license;
	GtkApplicationWindow* _tmp4_;
	const gchar* _tmp5_ = NULL;
	const gchar* _tmp6_ = NULL;
	const gchar* _tmp7_ = NULL;
	const gchar* _tmp8_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = g_strdup ("Robert Ancell");
	_tmp1_ = g_new0 (gchar*, 2 + 1);
	_tmp1_[0] = _tmp0_;
	_tmp1_[1] = NULL;
	authors = _tmp1_;
	authors_length1 = 2;
	_authors_size_ = authors_length1;
	_tmp2_ = _ ("This program is free software; you can redistribute it and/or modify i" \
"t under the terms of the GNU General Public License as published by th" \
"e Free Software Foundation; either version 2 of the License, or (at yo" \
"ur option) any later version.\n" \
"\n" \
"This program is distributed in the hope that it will be useful, but WI" \
"THOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILI" \
"TY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public Li" \
"cense for more details.\n" \
"\n" \
"You should have received a copy of the GNU General Public License alon" \
"g with this program; if not, write to the Free Software Foundation, In" \
"c., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA");
	_tmp3_ = g_strdup (_tmp2_);
	license = _tmp3_;
	_tmp4_ = self->priv->window;
	_tmp5_ = _ ("dconf Editor");
	_tmp6_ = _ ("Directly edit your entire configuration database");
	_tmp7_ = _ ("Copyright \xc2\xa9 Canonical Ltd");
	_tmp8_ = _ ("translator-credits");
	gtk_show_about_dialog ((GtkWindow*) _tmp4_, "program-name", _tmp5_, "version", VERSION, "comments", _tmp6_, "copyright", _tmp7_, "license", license, "wrap-license", TRUE, "authors", authors, "translator-credits", _tmp8_, "logo-icon-name", "dconf-editor", NULL, NULL);
	_g_free0 (license);
	authors = (_vala_array_free (authors, authors_length1, (GDestroyNotify) g_free), NULL);
}
