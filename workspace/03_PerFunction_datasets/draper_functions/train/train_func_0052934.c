print_latex_label(const label_state& style,
					const std::string& label,
					bool boxed) const
  {
    std::stringstream obuf;


    bool rotated(EPIX_EPSILON < fabs(style.label_angle()));


    bool masked(boxed && style.is_masked());


    bool padded(style.label_padding() != length(0));

    obuf << "\\makebox(0,0)"
	 << print(style.align_to());

    obuf << "{";

    if (rotated)
      obuf << "\\rotatebox{" << style.label_angle() << "}{";

    if (masked)
      {
	pen_data bpen(style.label_border());


	if (!bpen.color().is_unset() && length(EPIX_EPSILON) < bpen.width())
	  obuf << "\\fboxrule" << print(bpen.width()) << "%" << std::endl
	       << "\\fcolorbox{" << print(bpen.color()) << "}{"
	       << print(style.mask_color()) << "}";

	else
	  obuf << "\\colorbox{" << print(style.mask_color()) << "}";

	if (padded)
	  {

	    length extra_pad(style.label_padding() + length(-3));

	    obuf << "{\\fboxrule" << print(extra_pad) << "%" << std::endl
		 << "\\fcolorbox{" << print(style.mask_color()) << "}{"
		 << print(style.mask_color()) << "}";
	  }

	obuf << "{";
      }


    obuf << print_latex_hbox(style, label);


    if (masked)
      {
	obuf << "}";

	if (padded)
	  obuf << "}";
      }

    if (rotated)
      obuf << "}";

    obuf << "}";

    return obuf.str();
  }
