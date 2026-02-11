gf_smil_apply_additive(SMIL_Anim_RTI *rai)
{
	SMILAnimationAttributesPointers *animp = rai->animp;
	if (rai->change_detection_mode) return;
	else {


		if (animp->additive && *animp->additive == SMIL_ADDITIVE_SUM) {
			GF_LOG(GF_LOG_DEBUG, GF_LOG_SMIL,
				  ("[SMIL Animation] Time %f - Animation     %s - applying additive behavior\n",
				gf_node_get_scene_time((GF_Node*)rai->anim_elt), gf_node_get_log_name((GF_Node *)rai->anim_elt)));

			gf_svg_attributes_add((rai->is_first_anim ? &rai->owner->specified_value : &rai->owner->presentation_value),
								  &rai->interpolated_value,
								  &rai->owner->presentation_value,
								  1);

#ifndef GPAC_DISABLE_LOG
		if (gf_log_tool_level_on(GF_LOG_SMIL, GF_LOG_DEBUG)) {
			char *str;
			gf_log_lt(GF_LOG_DEBUG, GF_LOG_SMIL);
			str = gf_svg_dump_attribute((GF_Node*)rai->anim_elt, &rai->owner->presentation_value);
			gf_log("[SMIL Animation] Time %f - Animation     %s - Presentation value changed for attribute %s, new value: %s\n",
				gf_node_get_scene_time((GF_Node*)rai->anim_elt), gf_node_get_log_name((GF_Node*)rai->anim_elt),
				gf_svg_get_attribute_name((GF_Node*)rai->anim_elt, rai->owner->presentation_value.fieldIndex), str);

			if (str) gf_free(str);
		}
#endif

		} else {
			GF_LOG(GF_LOG_DEBUG, GF_LOG_SMIL,
				   ("[SMIL Animation] Time %f - Animation     %s - applying non-additive behavior\n",
				   gf_node_get_scene_time((GF_Node*)rai->anim_elt), gf_node_get_log_name((GF_Node *)rai->anim_elt)));


			gf_svg_attributes_copy(&rai->owner->presentation_value, &rai->interpolated_value, 1);
#ifndef GPAC_DISABLE_LOG
			if (gf_log_tool_level_on(GF_LOG_SMIL, GF_LOG_DEBUG)) {
				char *str;
				gf_log_lt(GF_LOG_DEBUG, GF_LOG_SMIL);
				str = gf_svg_dump_attribute((GF_Node*)rai->anim_elt, &rai->owner->presentation_value);

				gf_log("[SMIL Animation] Time %f - Animation     %s - Presentation value changed for attribute %s, new value: %s\n",
					gf_node_get_scene_time((GF_Node*)rai->anim_elt), gf_node_get_log_name((GF_Node*)rai->anim_elt),
					gf_svg_get_attribute_name((GF_Node*)rai->anim_elt, rai->owner->presentation_value.fieldIndex), str);

				if (str) gf_free(str);
			}
#endif
		}
	}
}
