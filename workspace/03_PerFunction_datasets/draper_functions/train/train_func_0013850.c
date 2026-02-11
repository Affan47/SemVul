localTranslate(glm::vec3 & t) {

	glm::mat4 transformation = glm::inverse(modelMatrix) * glm::mat4();
	transformation = glm::translate(glm::mat4(), t) * transformation;
	transformation = modelMatrix * transformation;


	position = glm::vec3(transformation * glm::vec4(position, 1));
	modelMatrix = transformation * modelMatrix;


	updateMatrices();
}
